; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_open_fd.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type opaque
%struct.write_fd_data = type { i32 }
%struct.stat = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %struct.timespec, %struct.timespec, %struct.timespec, [3 x i64] }
%struct.timespec = type { i64, i64 }

@.str = private unnamed_addr constant [10 x i8] c"No memory\00", align 1
@.str.1 = private unnamed_addr constant [20 x i8] c"Couldn't stat fd %d\00", align 1
@.str.2 = private unnamed_addr constant [12 x i8] c"Write error\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_open_fd(%struct.archive* %a, i32 %fd) #0 !dbg !11 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %fd.addr = alloca i32, align 4
  %mine = alloca %struct.write_fd_data*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !37, metadata !38), !dbg !39
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !40, metadata !38), !dbg !41
  call void @llvm.dbg.declare(metadata %struct.write_fd_data** %mine, metadata !42, metadata !38), !dbg !43
  %call = call noalias i8* @malloc(i64 4) #5, !dbg !44
  %0 = bitcast i8* %call to %struct.write_fd_data*, !dbg !45
  store %struct.write_fd_data* %0, %struct.write_fd_data** %mine, align 8, !dbg !46
  %1 = load %struct.write_fd_data*, %struct.write_fd_data** %mine, align 8, !dbg !47
  %cmp = icmp eq %struct.write_fd_data* %1, null, !dbg !49
  br i1 %cmp, label %if.then, label %if.end, !dbg !50

if.then:                                          ; preds = %entry
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !51
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %2, i32 12, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)), !dbg !53
  store i32 -30, i32* %retval, align 4, !dbg !54
  br label %return, !dbg !54

if.end:                                           ; preds = %entry
  %3 = load i32, i32* %fd.addr, align 4, !dbg !55
  %4 = load %struct.write_fd_data*, %struct.write_fd_data** %mine, align 8, !dbg !56
  %fd1 = getelementptr inbounds %struct.write_fd_data, %struct.write_fd_data* %4, i32 0, i32 0, !dbg !57
  store i32 %3, i32* %fd1, align 4, !dbg !58
  %5 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !59
  %6 = load %struct.write_fd_data*, %struct.write_fd_data** %mine, align 8, !dbg !60
  %7 = bitcast %struct.write_fd_data* %6 to i8*, !dbg !60
  %call2 = call i32 @archive_write_open(%struct.archive* %5, i8* %7, i32 (%struct.archive*, i8*)* @file_open, i64 (%struct.archive*, i8*, i8*, i64)* @file_write, i32 (%struct.archive*, i8*)* @file_close), !dbg !61
  store i32 %call2, i32* %retval, align 4, !dbg !62
  br label %return, !dbg !62

return:                                           ; preds = %if.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !63
  ret i32 %8, !dbg !63
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #2

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #3

declare i32 @archive_write_open(%struct.archive*, i8*, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*) #3

; Function Attrs: nounwind uwtable
define internal i32 @file_open(%struct.archive* %a, i8* %client_data) #0 !dbg !17 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %mine = alloca %struct.write_fd_data*, align 8
  %st = alloca %struct.stat, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !64, metadata !38), !dbg !65
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !66, metadata !38), !dbg !67
  call void @llvm.dbg.declare(metadata %struct.write_fd_data** %mine, metadata !68, metadata !38), !dbg !69
  call void @llvm.dbg.declare(metadata %struct.stat* %st, metadata !70, metadata !38), !dbg !109
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !110
  %1 = bitcast i8* %0 to %struct.write_fd_data*, !dbg !111
  store %struct.write_fd_data* %1, %struct.write_fd_data** %mine, align 8, !dbg !112
  %2 = load %struct.write_fd_data*, %struct.write_fd_data** %mine, align 8, !dbg !113
  %fd = getelementptr inbounds %struct.write_fd_data, %struct.write_fd_data* %2, i32 0, i32 0, !dbg !115
  %3 = load i32, i32* %fd, align 4, !dbg !115
  %call = call i32 @fstat(i32 %3, %struct.stat* %st) #5, !dbg !116
  %cmp = icmp ne i32 %call, 0, !dbg !117
  br i1 %cmp, label %if.then, label %if.end, !dbg !118

if.then:                                          ; preds = %entry
  %4 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !119
  %call1 = call i32* @__errno_location() #1, !dbg !121
  %5 = load i32, i32* %call1, align 4, !dbg !121
  %6 = load %struct.write_fd_data*, %struct.write_fd_data** %mine, align 8, !dbg !122
  %fd2 = getelementptr inbounds %struct.write_fd_data, %struct.write_fd_data* %6, i32 0, i32 0, !dbg !123
  %7 = load i32, i32* %fd2, align 4, !dbg !123
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %4, i32 %5, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.1, i32 0, i32 0), i32 %7), !dbg !124
  store i32 -30, i32* %retval, align 4, !dbg !126
  br label %return, !dbg !126

if.end:                                           ; preds = %entry
  %st_mode = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 3, !dbg !127
  %8 = load i32, i32* %st_mode, align 8, !dbg !127
  %and = and i32 %8, 61440, !dbg !127
  %cmp3 = icmp eq i32 %and, 32768, !dbg !127
  br i1 %cmp3, label %if.then4, label %if.end6, !dbg !129

if.then4:                                         ; preds = %if.end
  %9 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !130
  %st_dev = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 0, !dbg !131
  %10 = load i64, i64* %st_dev, align 8, !dbg !131
  %st_ino = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 1, !dbg !132
  %11 = load i64, i64* %st_ino, align 8, !dbg !132
  %call5 = call i32 @archive_write_set_skip_file(%struct.archive* %9, i64 %10, i64 %11), !dbg !133
  br label %if.end6, !dbg !133

if.end6:                                          ; preds = %if.then4, %if.end
  %12 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !134
  %call7 = call i32 @archive_write_get_bytes_in_last_block(%struct.archive* %12), !dbg !136
  %cmp8 = icmp slt i32 %call7, 0, !dbg !137
  br i1 %cmp8, label %if.then9, label %if.end27, !dbg !138

if.then9:                                         ; preds = %if.end6
  %st_mode10 = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 3, !dbg !139
  %13 = load i32, i32* %st_mode10, align 8, !dbg !139
  %and11 = and i32 %13, 61440, !dbg !139
  %cmp12 = icmp eq i32 %and11, 8192, !dbg !139
  br i1 %cmp12, label %if.then23, label %lor.lhs.false, !dbg !142

lor.lhs.false:                                    ; preds = %if.then9
  %st_mode13 = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 3, !dbg !143
  %14 = load i32, i32* %st_mode13, align 8, !dbg !143
  %and14 = and i32 %14, 61440, !dbg !143
  %cmp15 = icmp eq i32 %and14, 24576, !dbg !143
  br i1 %cmp15, label %if.then23, label %lor.lhs.false16, !dbg !145

lor.lhs.false16:                                  ; preds = %lor.lhs.false
  %st_mode17 = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 3, !dbg !146
  %15 = load i32, i32* %st_mode17, align 8, !dbg !146
  %and18 = and i32 %15, 61440, !dbg !146
  %cmp19 = icmp eq i32 %and18, 4096, !dbg !146
  br i1 %cmp19, label %if.then23, label %lor.lhs.false20, !dbg !147

lor.lhs.false20:                                  ; preds = %lor.lhs.false16
  %16 = load %struct.write_fd_data*, %struct.write_fd_data** %mine, align 8, !dbg !148
  %fd21 = getelementptr inbounds %struct.write_fd_data, %struct.write_fd_data* %16, i32 0, i32 0, !dbg !149
  %17 = load i32, i32* %fd21, align 4, !dbg !149
  %cmp22 = icmp eq i32 %17, 1, !dbg !150
  br i1 %cmp22, label %if.then23, label %if.else, !dbg !151

if.then23:                                        ; preds = %lor.lhs.false20, %lor.lhs.false16, %lor.lhs.false, %if.then9
  %18 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !153
  %call24 = call i32 @archive_write_set_bytes_in_last_block(%struct.archive* %18, i32 0), !dbg !154
  br label %if.end26, !dbg !154

if.else:                                          ; preds = %lor.lhs.false20
  %19 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !155
  %call25 = call i32 @archive_write_set_bytes_in_last_block(%struct.archive* %19, i32 1), !dbg !156
  br label %if.end26

if.end26:                                         ; preds = %if.else, %if.then23
  br label %if.end27, !dbg !157

if.end27:                                         ; preds = %if.end26, %if.end6
  store i32 0, i32* %retval, align 4, !dbg !158
  br label %return, !dbg !158

return:                                           ; preds = %if.end27, %if.then
  %20 = load i32, i32* %retval, align 4, !dbg !159
  ret i32 %20, !dbg !159
}

; Function Attrs: nounwind uwtable
define internal i64 @file_write(%struct.archive* %a, i8* %client_data, i8* %buff, i64 %length) #0 !dbg !20 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %buff.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  %mine = alloca %struct.write_fd_data*, align 8
  %bytesWritten = alloca i64, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !160, metadata !38), !dbg !161
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !162, metadata !38), !dbg !163
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !164, metadata !38), !dbg !165
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !166, metadata !38), !dbg !167
  call void @llvm.dbg.declare(metadata %struct.write_fd_data** %mine, metadata !168, metadata !38), !dbg !169
  call void @llvm.dbg.declare(metadata i64* %bytesWritten, metadata !170, metadata !38), !dbg !171
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !172
  %1 = bitcast i8* %0 to %struct.write_fd_data*, !dbg !173
  store %struct.write_fd_data* %1, %struct.write_fd_data** %mine, align 8, !dbg !174
  br label %for.cond, !dbg !175

for.cond:                                         ; preds = %if.then3, %entry
  %2 = load %struct.write_fd_data*, %struct.write_fd_data** %mine, align 8, !dbg !176
  %fd = getelementptr inbounds %struct.write_fd_data, %struct.write_fd_data* %2, i32 0, i32 0, !dbg !180
  %3 = load i32, i32* %fd, align 4, !dbg !180
  %4 = load i8*, i8** %buff.addr, align 8, !dbg !181
  %5 = load i64, i64* %length.addr, align 8, !dbg !182
  %call = call i64 @write(i32 %3, i8* %4, i64 %5), !dbg !183
  store i64 %call, i64* %bytesWritten, align 8, !dbg !184
  %6 = load i64, i64* %bytesWritten, align 8, !dbg !185
  %cmp = icmp sle i64 %6, 0, !dbg !187
  br i1 %cmp, label %if.then, label %if.end5, !dbg !188

if.then:                                          ; preds = %for.cond
  %call1 = call i32* @__errno_location() #1, !dbg !189
  %7 = load i32, i32* %call1, align 4, !dbg !189
  %cmp2 = icmp eq i32 %7, 4, !dbg !192
  br i1 %cmp2, label %if.then3, label %if.end, !dbg !193

if.then3:                                         ; preds = %if.then
  br label %for.cond, !dbg !194

if.end:                                           ; preds = %if.then
  %8 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !195
  %call4 = call i32* @__errno_location() #1, !dbg !196
  %9 = load i32, i32* %call4, align 4, !dbg !196
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %8, i32 %9, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.2, i32 0, i32 0)), !dbg !197
  store i64 -1, i64* %retval, align 8, !dbg !199
  br label %return, !dbg !199

if.end5:                                          ; preds = %for.cond
  %10 = load i64, i64* %bytesWritten, align 8, !dbg !200
  store i64 %10, i64* %retval, align 8, !dbg !201
  br label %return, !dbg !201

return:                                           ; preds = %if.end5, %if.end
  %11 = load i64, i64* %retval, align 8, !dbg !202
  ret i64 %11, !dbg !202
}

; Function Attrs: nounwind uwtable
define internal i32 @file_close(%struct.archive* %a, i8* %client_data) #0 !dbg !33 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %mine = alloca %struct.write_fd_data*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !203, metadata !38), !dbg !204
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !205, metadata !38), !dbg !206
  call void @llvm.dbg.declare(metadata %struct.write_fd_data** %mine, metadata !207, metadata !38), !dbg !208
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !209
  %1 = bitcast i8* %0 to %struct.write_fd_data*, !dbg !210
  store %struct.write_fd_data* %1, %struct.write_fd_data** %mine, align 8, !dbg !208
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !211
  %3 = load %struct.write_fd_data*, %struct.write_fd_data** %mine, align 8, !dbg !212
  %4 = bitcast %struct.write_fd_data* %3 to i8*, !dbg !212
  call void @free(i8* %4) #5, !dbg !213
  ret i32 0, !dbg !214
}

; Function Attrs: nounwind
declare i32 @fstat(i32, %struct.stat*) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #4

declare i32 @archive_write_set_skip_file(%struct.archive*, i64, i64) #3

declare i32 @archive_write_get_bytes_in_last_block(%struct.archive*) #3

declare i32 @archive_write_set_bytes_in_last_block(%struct.archive*, i32) #3

declare i64 @write(i32, i8*, i64) #3

; Function Attrs: nounwind
declare void @free(i8*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!34, !35}
!llvm.ident = !{!36}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !10)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_open_fd.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !9}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "write_fd_data", file: !1, line: 53, size: 32, align: 32, elements: !6)
!6 = !{!7}
!7 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !5, file: !1, line: 54, baseType: !8, size: 32, align: 32)
!8 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!10 = !{!11, !17, !20, !33}
!11 = distinct !DISubprogram(name: "archive_write_open_fd", scope: !1, file: !1, line: 62, type: !12, isLocal: false, isDefinition: true, scopeLine: 63, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!12 = !DISubroutineType(types: !13)
!13 = !{!8, !14, !8}
!14 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !15, size: 64, align: 64)
!15 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !16, line: 179, flags: DIFlagFwdDecl)
!16 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!17 = distinct !DISubprogram(name: "file_open", scope: !1, file: !1, line: 80, type: !18, isLocal: true, isDefinition: true, scopeLine: 81, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!18 = !DISubroutineType(types: !19)
!19 = !{!8, !14, !9}
!20 = distinct !DISubprogram(name: "file_write", scope: !1, file: !1, line: 118, type: !21, isLocal: true, isDefinition: true, scopeLine: 119, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!21 = !DISubroutineType(types: !22)
!22 = !{!23, !14, !9, !28, !30}
!23 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !24, line: 109, baseType: !25)
!24 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!25 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !26, line: 172, baseType: !27)
!26 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!27 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!28 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !29, size: 64, align: 64)
!29 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!30 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !31, line: 62, baseType: !32)
!31 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!32 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!33 = distinct !DISubprogram(name: "file_close", scope: !1, file: !1, line: 137, type: !18, isLocal: true, isDefinition: true, scopeLine: 138, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!34 = !{i32 2, !"Dwarf Version", i32 4}
!35 = !{i32 2, !"Debug Info Version", i32 3}
!36 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!37 = !DILocalVariable(name: "a", arg: 1, scope: !11, file: !1, line: 62, type: !14)
!38 = !DIExpression()
!39 = !DILocation(line: 62, column: 39, scope: !11)
!40 = !DILocalVariable(name: "fd", arg: 2, scope: !11, file: !1, line: 62, type: !8)
!41 = !DILocation(line: 62, column: 46, scope: !11)
!42 = !DILocalVariable(name: "mine", scope: !11, file: !1, line: 64, type: !4)
!43 = !DILocation(line: 64, column: 24, scope: !11)
!44 = !DILocation(line: 66, column: 33, scope: !11)
!45 = !DILocation(line: 66, column: 9, scope: !11)
!46 = !DILocation(line: 66, column: 7, scope: !11)
!47 = !DILocation(line: 67, column: 6, scope: !48)
!48 = distinct !DILexicalBlock(scope: !11, file: !1, line: 67, column: 6)
!49 = !DILocation(line: 67, column: 11, scope: !48)
!50 = !DILocation(line: 67, column: 6, scope: !11)
!51 = !DILocation(line: 68, column: 21, scope: !52)
!52 = distinct !DILexicalBlock(scope: !48, file: !1, line: 67, column: 20)
!53 = !DILocation(line: 68, column: 3, scope: !52)
!54 = !DILocation(line: 69, column: 3, scope: !52)
!55 = !DILocation(line: 71, column: 13, scope: !11)
!56 = !DILocation(line: 71, column: 2, scope: !11)
!57 = !DILocation(line: 71, column: 8, scope: !11)
!58 = !DILocation(line: 71, column: 11, scope: !11)
!59 = !DILocation(line: 75, column: 29, scope: !11)
!60 = !DILocation(line: 75, column: 32, scope: !11)
!61 = !DILocation(line: 75, column: 10, scope: !11)
!62 = !DILocation(line: 75, column: 2, scope: !11)
!63 = !DILocation(line: 77, column: 1, scope: !11)
!64 = !DILocalVariable(name: "a", arg: 1, scope: !17, file: !1, line: 80, type: !14)
!65 = !DILocation(line: 80, column: 27, scope: !17)
!66 = !DILocalVariable(name: "client_data", arg: 2, scope: !17, file: !1, line: 80, type: !9)
!67 = !DILocation(line: 80, column: 36, scope: !17)
!68 = !DILocalVariable(name: "mine", scope: !17, file: !1, line: 82, type: !4)
!69 = !DILocation(line: 82, column: 24, scope: !17)
!70 = !DILocalVariable(name: "st", scope: !17, file: !1, line: 83, type: !71)
!71 = !DICompositeType(tag: DW_TAG_structure_type, name: "stat", file: !72, line: 46, size: 1152, align: 64, elements: !73)
!72 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!73 = !{!74, !76, !78, !80, !83, !85, !87, !88, !89, !91, !93, !95, !103, !104, !105}
!74 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !71, file: !72, line: 48, baseType: !75, size: 64, align: 64)
!75 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !26, line: 124, baseType: !32)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !71, file: !72, line: 53, baseType: !77, size: 64, align: 64, offset: 64)
!77 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ino_t", file: !26, line: 127, baseType: !32)
!78 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !71, file: !72, line: 61, baseType: !79, size: 64, align: 64, offset: 128)
!79 = !DIDerivedType(tag: DW_TAG_typedef, name: "__nlink_t", file: !26, line: 130, baseType: !32)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !71, file: !72, line: 62, baseType: !81, size: 32, align: 32, offset: 192)
!81 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !26, line: 129, baseType: !82)
!82 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !71, file: !72, line: 64, baseType: !84, size: 32, align: 32, offset: 224)
!84 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !26, line: 125, baseType: !82)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !71, file: !72, line: 65, baseType: !86, size: 32, align: 32, offset: 256)
!86 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !26, line: 126, baseType: !82)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "__pad0", scope: !71, file: !72, line: 67, baseType: !8, size: 32, align: 32, offset: 288)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !71, file: !72, line: 69, baseType: !75, size: 64, align: 64, offset: 320)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !71, file: !72, line: 74, baseType: !90, size: 64, align: 64, offset: 384)
!90 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !26, line: 131, baseType: !27)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !71, file: !72, line: 78, baseType: !92, size: 64, align: 64, offset: 448)
!92 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blksize_t", file: !26, line: 153, baseType: !27)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !71, file: !72, line: 80, baseType: !94, size: 64, align: 64, offset: 512)
!94 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blkcnt_t", file: !26, line: 158, baseType: !27)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "st_atim", scope: !71, file: !72, line: 91, baseType: !96, size: 128, align: 64, offset: 576)
!96 = !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !97, line: 120, size: 128, align: 64, elements: !98)
!97 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!98 = !{!99, !101}
!99 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !96, file: !97, line: 122, baseType: !100, size: 64, align: 64)
!100 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !26, line: 139, baseType: !27)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !96, file: !97, line: 123, baseType: !102, size: 64, align: 64, offset: 64)
!102 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !26, line: 175, baseType: !27)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtim", scope: !71, file: !72, line: 92, baseType: !96, size: 128, align: 64, offset: 704)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctim", scope: !71, file: !72, line: 93, baseType: !96, size: 128, align: 64, offset: 832)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "__glibc_reserved", scope: !71, file: !72, line: 106, baseType: !106, size: 192, align: 64, offset: 960)
!106 = !DICompositeType(tag: DW_TAG_array_type, baseType: !102, size: 192, align: 64, elements: !107)
!107 = !{!108}
!108 = !DISubrange(count: 3)
!109 = !DILocation(line: 83, column: 14, scope: !17)
!110 = !DILocation(line: 85, column: 33, scope: !17)
!111 = !DILocation(line: 85, column: 9, scope: !17)
!112 = !DILocation(line: 85, column: 7, scope: !17)
!113 = !DILocation(line: 87, column: 12, scope: !114)
!114 = distinct !DILexicalBlock(scope: !17, file: !1, line: 87, column: 6)
!115 = !DILocation(line: 87, column: 18, scope: !114)
!116 = !DILocation(line: 87, column: 6, scope: !114)
!117 = !DILocation(line: 87, column: 27, scope: !114)
!118 = !DILocation(line: 87, column: 6, scope: !17)
!119 = !DILocation(line: 88, column: 21, scope: !120)
!120 = distinct !DILexicalBlock(scope: !114, file: !1, line: 87, column: 33)
!121 = !DILocation(line: 88, column: 24, scope: !120)
!122 = !DILocation(line: 88, column: 54, scope: !120)
!123 = !DILocation(line: 88, column: 60, scope: !120)
!124 = !DILocation(line: 88, column: 3, scope: !125)
!125 = !DILexicalBlockFile(scope: !120, file: !1, discriminator: 1)
!126 = !DILocation(line: 89, column: 3, scope: !120)
!127 = !DILocation(line: 95, column: 6, scope: !128)
!128 = distinct !DILexicalBlock(scope: !17, file: !1, line: 95, column: 6)
!129 = !DILocation(line: 95, column: 6, scope: !17)
!130 = !DILocation(line: 96, column: 31, scope: !128)
!131 = !DILocation(line: 96, column: 37, scope: !128)
!132 = !DILocation(line: 96, column: 48, scope: !128)
!133 = !DILocation(line: 96, column: 3, scope: !128)
!134 = !DILocation(line: 102, column: 44, scope: !135)
!135 = distinct !DILexicalBlock(scope: !17, file: !1, line: 102, column: 6)
!136 = !DILocation(line: 102, column: 6, scope: !135)
!137 = !DILocation(line: 102, column: 47, scope: !135)
!138 = !DILocation(line: 102, column: 6, scope: !17)
!139 = !DILocation(line: 106, column: 7, scope: !140)
!140 = distinct !DILexicalBlock(scope: !141, file: !1, line: 106, column: 7)
!141 = distinct !DILexicalBlock(scope: !135, file: !1, line: 102, column: 52)
!142 = !DILocation(line: 106, column: 27, scope: !140)
!143 = !DILocation(line: 106, column: 30, scope: !144)
!144 = !DILexicalBlockFile(scope: !140, file: !1, discriminator: 1)
!145 = !DILocation(line: 106, column: 50, scope: !144)
!146 = !DILocation(line: 107, column: 7, scope: !140)
!147 = !DILocation(line: 107, column: 28, scope: !140)
!148 = !DILocation(line: 107, column: 32, scope: !144)
!149 = !DILocation(line: 107, column: 38, scope: !144)
!150 = !DILocation(line: 107, column: 41, scope: !144)
!151 = !DILocation(line: 106, column: 7, scope: !152)
!152 = !DILexicalBlockFile(scope: !141, file: !1, discriminator: 2)
!153 = !DILocation(line: 109, column: 42, scope: !140)
!154 = !DILocation(line: 109, column: 4, scope: !140)
!155 = !DILocation(line: 111, column: 42, scope: !140)
!156 = !DILocation(line: 111, column: 4, scope: !140)
!157 = !DILocation(line: 112, column: 2, scope: !141)
!158 = !DILocation(line: 114, column: 2, scope: !17)
!159 = !DILocation(line: 115, column: 1, scope: !17)
!160 = !DILocalVariable(name: "a", arg: 1, scope: !20, file: !1, line: 118, type: !14)
!161 = !DILocation(line: 118, column: 28, scope: !20)
!162 = !DILocalVariable(name: "client_data", arg: 2, scope: !20, file: !1, line: 118, type: !9)
!163 = !DILocation(line: 118, column: 37, scope: !20)
!164 = !DILocalVariable(name: "buff", arg: 3, scope: !20, file: !1, line: 118, type: !28)
!165 = !DILocation(line: 118, column: 62, scope: !20)
!166 = !DILocalVariable(name: "length", arg: 4, scope: !20, file: !1, line: 118, type: !30)
!167 = !DILocation(line: 118, column: 75, scope: !20)
!168 = !DILocalVariable(name: "mine", scope: !20, file: !1, line: 120, type: !4)
!169 = !DILocation(line: 120, column: 24, scope: !20)
!170 = !DILocalVariable(name: "bytesWritten", scope: !20, file: !1, line: 121, type: !23)
!171 = !DILocation(line: 121, column: 10, scope: !20)
!172 = !DILocation(line: 123, column: 33, scope: !20)
!173 = !DILocation(line: 123, column: 9, scope: !20)
!174 = !DILocation(line: 123, column: 7, scope: !20)
!175 = !DILocation(line: 124, column: 2, scope: !20)
!176 = !DILocation(line: 125, column: 24, scope: !177)
!177 = distinct !DILexicalBlock(scope: !178, file: !1, line: 124, column: 11)
!178 = distinct !DILexicalBlock(scope: !179, file: !1, line: 124, column: 2)
!179 = distinct !DILexicalBlock(scope: !20, file: !1, line: 124, column: 2)
!180 = !DILocation(line: 125, column: 30, scope: !177)
!181 = !DILocation(line: 125, column: 34, scope: !177)
!182 = !DILocation(line: 125, column: 40, scope: !177)
!183 = !DILocation(line: 125, column: 18, scope: !177)
!184 = !DILocation(line: 125, column: 16, scope: !177)
!185 = !DILocation(line: 126, column: 7, scope: !186)
!186 = distinct !DILexicalBlock(scope: !177, file: !1, line: 126, column: 7)
!187 = !DILocation(line: 126, column: 20, scope: !186)
!188 = !DILocation(line: 126, column: 7, scope: !177)
!189 = !DILocation(line: 127, column: 8, scope: !190)
!190 = distinct !DILexicalBlock(scope: !191, file: !1, line: 127, column: 8)
!191 = distinct !DILexicalBlock(scope: !186, file: !1, line: 126, column: 26)
!192 = !DILocation(line: 127, column: 14, scope: !190)
!193 = !DILocation(line: 127, column: 8, scope: !191)
!194 = !DILocation(line: 128, column: 5, scope: !190)
!195 = !DILocation(line: 129, column: 22, scope: !191)
!196 = !DILocation(line: 129, column: 25, scope: !191)
!197 = !DILocation(line: 129, column: 4, scope: !198)
!198 = !DILexicalBlockFile(scope: !191, file: !1, discriminator: 1)
!199 = !DILocation(line: 130, column: 4, scope: !191)
!200 = !DILocation(line: 132, column: 11, scope: !177)
!201 = !DILocation(line: 132, column: 3, scope: !177)
!202 = !DILocation(line: 134, column: 1, scope: !20)
!203 = !DILocalVariable(name: "a", arg: 1, scope: !33, file: !1, line: 137, type: !14)
!204 = !DILocation(line: 137, column: 28, scope: !33)
!205 = !DILocalVariable(name: "client_data", arg: 2, scope: !33, file: !1, line: 137, type: !9)
!206 = !DILocation(line: 137, column: 37, scope: !33)
!207 = !DILocalVariable(name: "mine", scope: !33, file: !1, line: 139, type: !4)
!208 = !DILocation(line: 139, column: 24, scope: !33)
!209 = !DILocation(line: 139, column: 55, scope: !33)
!210 = !DILocation(line: 139, column: 31, scope: !33)
!211 = !DILocation(line: 141, column: 8, scope: !33)
!212 = !DILocation(line: 142, column: 7, scope: !33)
!213 = !DILocation(line: 142, column: 2, scope: !33)
!214 = !DILocation(line: 143, column: 2, scope: !33)
