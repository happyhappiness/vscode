; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/strcase.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define signext i8 @Curl_raw_toupper(i8 signext %in) #0 !dbg !7 {
entry:
  %retval = alloca i8, align 1
  %in.addr = alloca i8, align 1
  store i8 %in, i8* %in.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %in.addr, metadata !32, metadata !33), !dbg !34
  %0 = load i8, i8* %in.addr, align 1, !dbg !35
  %conv = sext i8 %0 to i32, !dbg !35
  %cmp = icmp sge i32 %conv, 97, !dbg !37
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !38

land.lhs.true:                                    ; preds = %entry
  %1 = load i8, i8* %in.addr, align 1, !dbg !39
  %conv2 = sext i8 %1 to i32, !dbg !39
  %cmp3 = icmp sle i32 %conv2, 122, !dbg !41
  br i1 %cmp3, label %if.then, label %if.end, !dbg !42

if.then:                                          ; preds = %land.lhs.true
  %2 = load i8, i8* %in.addr, align 1, !dbg !43
  %conv5 = sext i8 %2 to i32, !dbg !43
  %add = add nsw i32 65, %conv5, !dbg !44
  %sub = sub nsw i32 %add, 97, !dbg !45
  %conv6 = trunc i32 %sub to i8, !dbg !46
  store i8 %conv6, i8* %retval, align 1, !dbg !47
  br label %return, !dbg !47

if.end:                                           ; preds = %land.lhs.true, %entry
  %3 = load i8, i8* %in.addr, align 1, !dbg !48
  store i8 %3, i8* %retval, align 1, !dbg !49
  br label %return, !dbg !49

return:                                           ; preds = %if.end, %if.then
  %4 = load i8, i8* %retval, align 1, !dbg !50
  ret i8 %4, !dbg !50
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @Curl_strcasecompare(i8* %first, i8* %second) #0 !dbg !10 {
entry:
  %first.addr = alloca i8*, align 8
  %second.addr = alloca i8*, align 8
  store i8* %first, i8** %first.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %first.addr, metadata !51, metadata !33), !dbg !52
  store i8* %second, i8** %second.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %second.addr, metadata !53, metadata !33), !dbg !54
  br label %while.cond, !dbg !55

while.cond:                                       ; preds = %if.end, %entry
  %0 = load i8*, i8** %first.addr, align 8, !dbg !56
  %1 = load i8, i8* %0, align 1, !dbg !58
  %conv = sext i8 %1 to i32, !dbg !58
  %tobool = icmp ne i32 %conv, 0, !dbg !58
  br i1 %tobool, label %land.rhs, label %land.end, !dbg !59

land.rhs:                                         ; preds = %while.cond
  %2 = load i8*, i8** %second.addr, align 8, !dbg !60
  %3 = load i8, i8* %2, align 1, !dbg !62
  %conv1 = sext i8 %3 to i32, !dbg !62
  %tobool2 = icmp ne i32 %conv1, 0, !dbg !63
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %4 = phi i1 [ false, %while.cond ], [ %tobool2, %land.rhs ]
  br i1 %4, label %while.body, label %while.end, !dbg !64

while.body:                                       ; preds = %land.end
  %5 = load i8*, i8** %first.addr, align 8, !dbg !66
  %6 = load i8, i8* %5, align 1, !dbg !69
  %call = call signext i8 @Curl_raw_toupper(i8 signext %6), !dbg !70
  %conv3 = sext i8 %call to i32, !dbg !70
  %7 = load i8*, i8** %second.addr, align 8, !dbg !71
  %8 = load i8, i8* %7, align 1, !dbg !72
  %call4 = call signext i8 @Curl_raw_toupper(i8 signext %8), !dbg !73
  %conv5 = sext i8 %call4 to i32, !dbg !75
  %cmp = icmp ne i32 %conv3, %conv5, !dbg !76
  br i1 %cmp, label %if.then, label %if.end, !dbg !77

if.then:                                          ; preds = %while.body
  br label %while.end, !dbg !78

if.end:                                           ; preds = %while.body
  %9 = load i8*, i8** %first.addr, align 8, !dbg !79
  %incdec.ptr = getelementptr inbounds i8, i8* %9, i32 1, !dbg !79
  store i8* %incdec.ptr, i8** %first.addr, align 8, !dbg !79
  %10 = load i8*, i8** %second.addr, align 8, !dbg !80
  %incdec.ptr7 = getelementptr inbounds i8, i8* %10, i32 1, !dbg !80
  store i8* %incdec.ptr7, i8** %second.addr, align 8, !dbg !80
  br label %while.cond, !dbg !81

while.end:                                        ; preds = %if.then, %land.end
  %11 = load i8*, i8** %first.addr, align 8, !dbg !83
  %12 = load i8, i8* %11, align 1, !dbg !84
  %call8 = call signext i8 @Curl_raw_toupper(i8 signext %12), !dbg !85
  %conv9 = sext i8 %call8 to i32, !dbg !85
  %13 = load i8*, i8** %second.addr, align 8, !dbg !86
  %14 = load i8, i8* %13, align 1, !dbg !87
  %call10 = call signext i8 @Curl_raw_toupper(i8 signext %14), !dbg !88
  %conv11 = sext i8 %call10 to i32, !dbg !89
  %cmp12 = icmp eq i32 %conv9, %conv11, !dbg !90
  %conv13 = zext i1 %cmp12 to i32, !dbg !90
  ret i32 %conv13, !dbg !91
}

; Function Attrs: nounwind uwtable
define i32 @Curl_safe_strcasecompare(i8* %first, i8* %second) #0 !dbg !16 {
entry:
  %retval = alloca i32, align 4
  %first.addr = alloca i8*, align 8
  %second.addr = alloca i8*, align 8
  store i8* %first, i8** %first.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %first.addr, metadata !92, metadata !33), !dbg !93
  store i8* %second, i8** %second.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %second.addr, metadata !94, metadata !33), !dbg !95
  %0 = load i8*, i8** %first.addr, align 8, !dbg !96
  %tobool = icmp ne i8* %0, null, !dbg !96
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !98

land.lhs.true:                                    ; preds = %entry
  %1 = load i8*, i8** %second.addr, align 8, !dbg !99
  %tobool1 = icmp ne i8* %1, null, !dbg !99
  br i1 %tobool1, label %if.then, label %if.end, !dbg !101

if.then:                                          ; preds = %land.lhs.true
  %2 = load i8*, i8** %first.addr, align 8, !dbg !102
  %3 = load i8*, i8** %second.addr, align 8, !dbg !103
  %call = call i32 @Curl_strcasecompare(i8* %2, i8* %3), !dbg !104
  store i32 %call, i32* %retval, align 4, !dbg !105
  br label %return, !dbg !105

if.end:                                           ; preds = %land.lhs.true, %entry
  %4 = load i8*, i8** %first.addr, align 8, !dbg !106
  %cmp = icmp eq i8* null, %4, !dbg !107
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !108

land.rhs:                                         ; preds = %if.end
  %5 = load i8*, i8** %second.addr, align 8, !dbg !109
  %cmp2 = icmp eq i8* null, %5, !dbg !111
  br label %land.end

land.end:                                         ; preds = %land.rhs, %if.end
  %6 = phi i1 [ false, %if.end ], [ %cmp2, %land.rhs ]
  %land.ext = zext i1 %6 to i32, !dbg !112
  store i32 %land.ext, i32* %retval, align 4, !dbg !114
  br label %return, !dbg !114

return:                                           ; preds = %land.end, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !115
  ret i32 %7, !dbg !115
}

; Function Attrs: nounwind uwtable
define i32 @Curl_strncasecompare(i8* %first, i8* %second, i64 %max) #0 !dbg !17 {
entry:
  %retval = alloca i32, align 4
  %first.addr = alloca i8*, align 8
  %second.addr = alloca i8*, align 8
  %max.addr = alloca i64, align 8
  store i8* %first, i8** %first.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %first.addr, metadata !116, metadata !33), !dbg !117
  store i8* %second, i8** %second.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %second.addr, metadata !118, metadata !33), !dbg !119
  store i64 %max, i64* %max.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %max.addr, metadata !120, metadata !33), !dbg !121
  br label %while.cond, !dbg !122

while.cond:                                       ; preds = %if.end, %entry
  %0 = load i8*, i8** %first.addr, align 8, !dbg !123
  %1 = load i8, i8* %0, align 1, !dbg !125
  %conv = sext i8 %1 to i32, !dbg !125
  %tobool = icmp ne i32 %conv, 0, !dbg !125
  br i1 %tobool, label %land.lhs.true, label %land.end, !dbg !126

land.lhs.true:                                    ; preds = %while.cond
  %2 = load i8*, i8** %second.addr, align 8, !dbg !127
  %3 = load i8, i8* %2, align 1, !dbg !129
  %conv1 = sext i8 %3 to i32, !dbg !129
  %tobool2 = icmp ne i32 %conv1, 0, !dbg !129
  br i1 %tobool2, label %land.rhs, label %land.end, !dbg !130

land.rhs:                                         ; preds = %land.lhs.true
  %4 = load i64, i64* %max.addr, align 8, !dbg !131
  %tobool3 = icmp ne i64 %4, 0, !dbg !133
  br label %land.end

land.end:                                         ; preds = %land.rhs, %land.lhs.true, %while.cond
  %5 = phi i1 [ false, %land.lhs.true ], [ false, %while.cond ], [ %tobool3, %land.rhs ]
  br i1 %5, label %while.body, label %while.end, !dbg !134

while.body:                                       ; preds = %land.end
  %6 = load i8*, i8** %first.addr, align 8, !dbg !136
  %7 = load i8, i8* %6, align 1, !dbg !139
  %call = call signext i8 @Curl_raw_toupper(i8 signext %7), !dbg !140
  %conv4 = sext i8 %call to i32, !dbg !140
  %8 = load i8*, i8** %second.addr, align 8, !dbg !141
  %9 = load i8, i8* %8, align 1, !dbg !142
  %call5 = call signext i8 @Curl_raw_toupper(i8 signext %9), !dbg !143
  %conv6 = sext i8 %call5 to i32, !dbg !145
  %cmp = icmp ne i32 %conv4, %conv6, !dbg !146
  br i1 %cmp, label %if.then, label %if.end, !dbg !147

if.then:                                          ; preds = %while.body
  br label %while.end, !dbg !148

if.end:                                           ; preds = %while.body
  %10 = load i64, i64* %max.addr, align 8, !dbg !150
  %dec = add i64 %10, -1, !dbg !150
  store i64 %dec, i64* %max.addr, align 8, !dbg !150
  %11 = load i8*, i8** %first.addr, align 8, !dbg !151
  %incdec.ptr = getelementptr inbounds i8, i8* %11, i32 1, !dbg !151
  store i8* %incdec.ptr, i8** %first.addr, align 8, !dbg !151
  %12 = load i8*, i8** %second.addr, align 8, !dbg !152
  %incdec.ptr8 = getelementptr inbounds i8, i8* %12, i32 1, !dbg !152
  store i8* %incdec.ptr8, i8** %second.addr, align 8, !dbg !152
  br label %while.cond, !dbg !153

while.end:                                        ; preds = %if.then, %land.end
  %13 = load i64, i64* %max.addr, align 8, !dbg !155
  %cmp9 = icmp eq i64 0, %13, !dbg !157
  br i1 %cmp9, label %if.then11, label %if.end12, !dbg !158

if.then11:                                        ; preds = %while.end
  store i32 1, i32* %retval, align 4, !dbg !159
  br label %return, !dbg !159

if.end12:                                         ; preds = %while.end
  %14 = load i8*, i8** %first.addr, align 8, !dbg !160
  %15 = load i8, i8* %14, align 1, !dbg !161
  %call13 = call signext i8 @Curl_raw_toupper(i8 signext %15), !dbg !162
  %conv14 = sext i8 %call13 to i32, !dbg !162
  %16 = load i8*, i8** %second.addr, align 8, !dbg !163
  %17 = load i8, i8* %16, align 1, !dbg !164
  %call15 = call signext i8 @Curl_raw_toupper(i8 signext %17), !dbg !165
  %conv16 = sext i8 %call15 to i32, !dbg !166
  %cmp17 = icmp eq i32 %conv14, %conv16, !dbg !167
  %conv18 = zext i1 %cmp17 to i32, !dbg !167
  store i32 %conv18, i32* %retval, align 4, !dbg !168
  br label %return, !dbg !168

return:                                           ; preds = %if.end12, %if.then11
  %18 = load i32, i32* %retval, align 4, !dbg !169
  ret i32 %18, !dbg !169
}

; Function Attrs: nounwind uwtable
define void @Curl_strntoupper(i8* %dest, i8* %src, i64 %n) #0 !dbg !23 {
entry:
  %dest.addr = alloca i8*, align 8
  %src.addr = alloca i8*, align 8
  %n.addr = alloca i64, align 8
  store i8* %dest, i8** %dest.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dest.addr, metadata !170, metadata !33), !dbg !171
  store i8* %src, i8** %src.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %src.addr, metadata !172, metadata !33), !dbg !173
  store i64 %n, i64* %n.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %n.addr, metadata !174, metadata !33), !dbg !175
  %0 = load i64, i64* %n.addr, align 8, !dbg !176
  %cmp = icmp ult i64 %0, 1, !dbg !178
  br i1 %cmp, label %if.then, label %if.end, !dbg !179

if.then:                                          ; preds = %entry
  br label %do.end, !dbg !180

if.end:                                           ; preds = %entry
  br label %do.body, !dbg !181

do.body:                                          ; preds = %land.end, %if.end
  %1 = load i8*, i8** %src.addr, align 8, !dbg !182
  %2 = load i8, i8* %1, align 1, !dbg !184
  %call = call signext i8 @Curl_raw_toupper(i8 signext %2), !dbg !185
  %3 = load i8*, i8** %dest.addr, align 8, !dbg !186
  %incdec.ptr = getelementptr inbounds i8, i8* %3, i32 1, !dbg !186
  store i8* %incdec.ptr, i8** %dest.addr, align 8, !dbg !186
  store i8 %call, i8* %3, align 1, !dbg !187
  br label %do.cond, !dbg !188

do.cond:                                          ; preds = %do.body
  %4 = load i8*, i8** %src.addr, align 8, !dbg !189
  %incdec.ptr1 = getelementptr inbounds i8, i8* %4, i32 1, !dbg !189
  store i8* %incdec.ptr1, i8** %src.addr, align 8, !dbg !189
  %5 = load i8, i8* %4, align 1, !dbg !191
  %conv = sext i8 %5 to i32, !dbg !191
  %tobool = icmp ne i32 %conv, 0, !dbg !191
  br i1 %tobool, label %land.rhs, label %land.end, !dbg !192

land.rhs:                                         ; preds = %do.cond
  %6 = load i64, i64* %n.addr, align 8, !dbg !193
  %dec = add i64 %6, -1, !dbg !193
  store i64 %dec, i64* %n.addr, align 8, !dbg !193
  %tobool2 = icmp ne i64 %dec, 0, !dbg !195
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %7 = phi i1 [ false, %do.cond ], [ %tobool2, %land.rhs ]
  br i1 %7, label %do.body, label %do.end, !dbg !196

do.end:                                           ; preds = %if.then, %land.end
  ret void, !dbg !198
}

; Function Attrs: nounwind uwtable
define i32 @curl_strequal(i8* %first, i8* %second) #0 !dbg !27 {
entry:
  %first.addr = alloca i8*, align 8
  %second.addr = alloca i8*, align 8
  store i8* %first, i8** %first.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %first.addr, metadata !199, metadata !33), !dbg !200
  store i8* %second, i8** %second.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %second.addr, metadata !201, metadata !33), !dbg !202
  %0 = load i8*, i8** %first.addr, align 8, !dbg !203
  %1 = load i8*, i8** %second.addr, align 8, !dbg !204
  %call = call i32 @Curl_strcasecompare(i8* %0, i8* %1), !dbg !205
  ret i32 %call, !dbg !206
}

; Function Attrs: nounwind uwtable
define i32 @curl_strnequal(i8* %first, i8* %second, i64 %max) #0 !dbg !28 {
entry:
  %first.addr = alloca i8*, align 8
  %second.addr = alloca i8*, align 8
  %max.addr = alloca i64, align 8
  store i8* %first, i8** %first.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %first.addr, metadata !207, metadata !33), !dbg !208
  store i8* %second, i8** %second.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %second.addr, metadata !209, metadata !33), !dbg !210
  store i64 %max, i64* %max.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %max.addr, metadata !211, metadata !33), !dbg !212
  %0 = load i8*, i8** %first.addr, align 8, !dbg !213
  %1 = load i8*, i8** %second.addr, align 8, !dbg !214
  %2 = load i64, i64* %max.addr, align 8, !dbg !215
  %call = call i32 @Curl_strncasecompare(i8* %0, i8* %1, i64 %2), !dbg !216
  ret i32 %call, !dbg !217
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!29, !30}
!llvm.ident = !{!31}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !6)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/strcase.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{}
!3 = !{!4, !5}
!4 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!6 = !{!7, !10, !16, !17, !23, !27, !28}
!7 = distinct !DISubprogram(name: "Curl_raw_toupper", scope: !1, file: !1, line: 31, type: !8, isLocal: false, isDefinition: true, scopeLine: 32, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!8 = !DISubroutineType(types: !9)
!9 = !{!4, !4}
!10 = distinct !DISubprogram(name: "Curl_strcasecompare", scope: !1, file: !1, line: 108, type: !11, isLocal: false, isDefinition: true, scopeLine: 109, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!11 = !DISubroutineType(types: !12)
!12 = !{!13, !14, !14}
!13 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!14 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !15, size: 64, align: 64)
!15 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !4)
!16 = distinct !DISubprogram(name: "Curl_safe_strcasecompare", scope: !1, file: !1, line: 123, type: !11, isLocal: false, isDefinition: true, scopeLine: 124, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!17 = distinct !DISubprogram(name: "Curl_strncasecompare", scope: !1, file: !1, line: 136, type: !18, isLocal: false, isDefinition: true, scopeLine: 137, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!18 = !DISubroutineType(types: !19)
!19 = !{!13, !14, !14, !20}
!20 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !21, line: 62, baseType: !22)
!21 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!22 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!23 = distinct !DISubprogram(name: "Curl_strntoupper", scope: !1, file: !1, line: 157, type: !24, isLocal: false, isDefinition: true, scopeLine: 158, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!24 = !DISubroutineType(types: !25)
!25 = !{null, !26, !14, !20}
!26 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !4, size: 64, align: 64)
!27 = distinct !DISubprogram(name: "curl_strequal", scope: !1, file: !1, line: 169, type: !11, isLocal: false, isDefinition: true, scopeLine: 170, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!28 = distinct !DISubprogram(name: "curl_strnequal", scope: !1, file: !1, line: 173, type: !18, isLocal: false, isDefinition: true, scopeLine: 174, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!29 = !{i32 2, !"Dwarf Version", i32 4}
!30 = !{i32 2, !"Debug Info Version", i32 3}
!31 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!32 = !DILocalVariable(name: "in", arg: 1, scope: !7, file: !1, line: 31, type: !4)
!33 = !DIExpression()
!34 = !DILocation(line: 31, column: 28, scope: !7)
!35 = !DILocation(line: 34, column: 6, scope: !36)
!36 = distinct !DILexicalBlock(scope: !7, file: !1, line: 34, column: 6)
!37 = !DILocation(line: 34, column: 9, scope: !36)
!38 = !DILocation(line: 34, column: 16, scope: !36)
!39 = !DILocation(line: 34, column: 19, scope: !40)
!40 = !DILexicalBlockFile(scope: !36, file: !1, discriminator: 1)
!41 = !DILocation(line: 34, column: 22, scope: !40)
!42 = !DILocation(line: 34, column: 6, scope: !40)
!43 = !DILocation(line: 35, column: 25, scope: !36)
!44 = !DILocation(line: 35, column: 23, scope: !36)
!45 = !DILocation(line: 35, column: 28, scope: !36)
!46 = !DILocation(line: 35, column: 12, scope: !36)
!47 = !DILocation(line: 35, column: 5, scope: !36)
!48 = !DILocation(line: 93, column: 10, scope: !7)
!49 = !DILocation(line: 93, column: 3, scope: !7)
!50 = !DILocation(line: 94, column: 1, scope: !7)
!51 = !DILocalVariable(name: "first", arg: 1, scope: !10, file: !1, line: 108, type: !14)
!52 = !DILocation(line: 108, column: 37, scope: !10)
!53 = !DILocalVariable(name: "second", arg: 2, scope: !10, file: !1, line: 108, type: !14)
!54 = !DILocation(line: 108, column: 56, scope: !10)
!55 = !DILocation(line: 110, column: 3, scope: !10)
!56 = !DILocation(line: 110, column: 10, scope: !57)
!57 = !DILexicalBlockFile(scope: !10, file: !1, discriminator: 1)
!58 = !DILocation(line: 110, column: 9, scope: !57)
!59 = !DILocation(line: 110, column: 16, scope: !57)
!60 = !DILocation(line: 110, column: 20, scope: !61)
!61 = !DILexicalBlockFile(scope: !10, file: !1, discriminator: 2)
!62 = !DILocation(line: 110, column: 19, scope: !61)
!63 = !DILocation(line: 110, column: 16, scope: !61)
!64 = !DILocation(line: 110, column: 3, scope: !65)
!65 = !DILexicalBlockFile(scope: !10, file: !1, discriminator: 3)
!66 = !DILocation(line: 111, column: 26, scope: !67)
!67 = distinct !DILexicalBlock(scope: !68, file: !1, line: 111, column: 8)
!68 = distinct !DILexicalBlock(scope: !10, file: !1, line: 110, column: 28)
!69 = !DILocation(line: 111, column: 25, scope: !67)
!70 = !DILocation(line: 111, column: 8, scope: !67)
!71 = !DILocation(line: 111, column: 54, scope: !67)
!72 = !DILocation(line: 111, column: 53, scope: !67)
!73 = !DILocation(line: 111, column: 36, scope: !74)
!74 = !DILexicalBlockFile(scope: !67, file: !1, discriminator: 1)
!75 = !DILocation(line: 111, column: 36, scope: !67)
!76 = !DILocation(line: 111, column: 33, scope: !67)
!77 = !DILocation(line: 111, column: 8, scope: !68)
!78 = !DILocation(line: 113, column: 7, scope: !67)
!79 = !DILocation(line: 114, column: 10, scope: !68)
!80 = !DILocation(line: 115, column: 11, scope: !68)
!81 = !DILocation(line: 110, column: 3, scope: !82)
!82 = !DILexicalBlockFile(scope: !10, file: !1, discriminator: 4)
!83 = !DILocation(line: 120, column: 29, scope: !10)
!84 = !DILocation(line: 120, column: 28, scope: !10)
!85 = !DILocation(line: 120, column: 11, scope: !10)
!86 = !DILocation(line: 120, column: 57, scope: !10)
!87 = !DILocation(line: 120, column: 56, scope: !10)
!88 = !DILocation(line: 120, column: 39, scope: !57)
!89 = !DILocation(line: 120, column: 39, scope: !10)
!90 = !DILocation(line: 120, column: 36, scope: !10)
!91 = !DILocation(line: 120, column: 3, scope: !10)
!92 = !DILocalVariable(name: "first", arg: 1, scope: !16, file: !1, line: 123, type: !14)
!93 = !DILocation(line: 123, column: 42, scope: !16)
!94 = !DILocalVariable(name: "second", arg: 2, scope: !16, file: !1, line: 123, type: !14)
!95 = !DILocation(line: 123, column: 61, scope: !16)
!96 = !DILocation(line: 125, column: 6, scope: !97)
!97 = distinct !DILexicalBlock(scope: !16, file: !1, line: 125, column: 6)
!98 = !DILocation(line: 125, column: 12, scope: !97)
!99 = !DILocation(line: 125, column: 15, scope: !100)
!100 = !DILexicalBlockFile(scope: !97, file: !1, discriminator: 1)
!101 = !DILocation(line: 125, column: 6, scope: !100)
!102 = !DILocation(line: 127, column: 32, scope: !97)
!103 = !DILocation(line: 127, column: 39, scope: !97)
!104 = !DILocation(line: 127, column: 12, scope: !97)
!105 = !DILocation(line: 127, column: 5, scope: !97)
!106 = !DILocation(line: 130, column: 19, scope: !16)
!107 = !DILocation(line: 130, column: 16, scope: !16)
!108 = !DILocation(line: 130, column: 25, scope: !16)
!109 = !DILocation(line: 130, column: 36, scope: !110)
!110 = !DILexicalBlockFile(scope: !16, file: !1, discriminator: 1)
!111 = !DILocation(line: 130, column: 33, scope: !110)
!112 = !DILocation(line: 130, column: 25, scope: !113)
!113 = !DILexicalBlockFile(scope: !16, file: !1, discriminator: 2)
!114 = !DILocation(line: 130, column: 3, scope: !113)
!115 = !DILocation(line: 131, column: 1, scope: !16)
!116 = !DILocalVariable(name: "first", arg: 1, scope: !17, file: !1, line: 136, type: !14)
!117 = !DILocation(line: 136, column: 38, scope: !17)
!118 = !DILocalVariable(name: "second", arg: 2, scope: !17, file: !1, line: 136, type: !14)
!119 = !DILocation(line: 136, column: 57, scope: !17)
!120 = !DILocalVariable(name: "max", arg: 3, scope: !17, file: !1, line: 136, type: !20)
!121 = !DILocation(line: 136, column: 72, scope: !17)
!122 = !DILocation(line: 138, column: 3, scope: !17)
!123 = !DILocation(line: 138, column: 10, scope: !124)
!124 = !DILexicalBlockFile(scope: !17, file: !1, discriminator: 1)
!125 = !DILocation(line: 138, column: 9, scope: !124)
!126 = !DILocation(line: 138, column: 16, scope: !124)
!127 = !DILocation(line: 138, column: 20, scope: !128)
!128 = !DILexicalBlockFile(scope: !17, file: !1, discriminator: 2)
!129 = !DILocation(line: 138, column: 19, scope: !128)
!130 = !DILocation(line: 138, column: 27, scope: !128)
!131 = !DILocation(line: 138, column: 30, scope: !132)
!132 = !DILexicalBlockFile(scope: !17, file: !1, discriminator: 3)
!133 = !DILocation(line: 138, column: 27, scope: !132)
!134 = !DILocation(line: 138, column: 3, scope: !135)
!135 = !DILexicalBlockFile(scope: !17, file: !1, discriminator: 4)
!136 = !DILocation(line: 139, column: 26, scope: !137)
!137 = distinct !DILexicalBlock(scope: !138, file: !1, line: 139, column: 8)
!138 = distinct !DILexicalBlock(scope: !17, file: !1, line: 138, column: 35)
!139 = !DILocation(line: 139, column: 25, scope: !137)
!140 = !DILocation(line: 139, column: 8, scope: !137)
!141 = !DILocation(line: 139, column: 54, scope: !137)
!142 = !DILocation(line: 139, column: 53, scope: !137)
!143 = !DILocation(line: 139, column: 36, scope: !144)
!144 = !DILexicalBlockFile(scope: !137, file: !1, discriminator: 1)
!145 = !DILocation(line: 139, column: 36, scope: !137)
!146 = !DILocation(line: 139, column: 33, scope: !137)
!147 = !DILocation(line: 139, column: 8, scope: !138)
!148 = !DILocation(line: 140, column: 7, scope: !149)
!149 = distinct !DILexicalBlock(scope: !137, file: !1, line: 139, column: 63)
!150 = !DILocation(line: 142, column: 8, scope: !138)
!151 = !DILocation(line: 143, column: 10, scope: !138)
!152 = !DILocation(line: 144, column: 11, scope: !138)
!153 = !DILocation(line: 138, column: 3, scope: !154)
!154 = !DILexicalBlockFile(scope: !17, file: !1, discriminator: 5)
!155 = !DILocation(line: 146, column: 11, scope: !156)
!156 = distinct !DILexicalBlock(scope: !17, file: !1, line: 146, column: 6)
!157 = !DILocation(line: 146, column: 8, scope: !156)
!158 = !DILocation(line: 146, column: 6, scope: !17)
!159 = !DILocation(line: 147, column: 5, scope: !156)
!160 = !DILocation(line: 149, column: 28, scope: !17)
!161 = !DILocation(line: 149, column: 27, scope: !17)
!162 = !DILocation(line: 149, column: 10, scope: !17)
!163 = !DILocation(line: 149, column: 56, scope: !17)
!164 = !DILocation(line: 149, column: 55, scope: !17)
!165 = !DILocation(line: 149, column: 38, scope: !124)
!166 = !DILocation(line: 149, column: 38, scope: !17)
!167 = !DILocation(line: 149, column: 35, scope: !17)
!168 = !DILocation(line: 149, column: 3, scope: !17)
!169 = !DILocation(line: 150, column: 1, scope: !17)
!170 = !DILocalVariable(name: "dest", arg: 1, scope: !23, file: !1, line: 157, type: !26)
!171 = !DILocation(line: 157, column: 29, scope: !23)
!172 = !DILocalVariable(name: "src", arg: 2, scope: !23, file: !1, line: 157, type: !14)
!173 = !DILocation(line: 157, column: 47, scope: !23)
!174 = !DILocalVariable(name: "n", arg: 3, scope: !23, file: !1, line: 157, type: !20)
!175 = !DILocation(line: 157, column: 59, scope: !23)
!176 = !DILocation(line: 159, column: 6, scope: !177)
!177 = distinct !DILexicalBlock(scope: !23, file: !1, line: 159, column: 6)
!178 = !DILocation(line: 159, column: 8, scope: !177)
!179 = !DILocation(line: 159, column: 6, scope: !23)
!180 = !DILocation(line: 160, column: 5, scope: !177)
!181 = !DILocation(line: 162, column: 3, scope: !23)
!182 = !DILocation(line: 163, column: 33, scope: !183)
!183 = distinct !DILexicalBlock(scope: !23, file: !1, line: 162, column: 6)
!184 = !DILocation(line: 163, column: 32, scope: !183)
!185 = !DILocation(line: 163, column: 15, scope: !183)
!186 = !DILocation(line: 163, column: 10, scope: !183)
!187 = !DILocation(line: 163, column: 13, scope: !183)
!188 = !DILocation(line: 164, column: 3, scope: !183)
!189 = !DILocation(line: 164, column: 15, scope: !190)
!190 = !DILexicalBlockFile(scope: !23, file: !1, discriminator: 1)
!191 = !DILocation(line: 164, column: 11, scope: !190)
!192 = !DILocation(line: 164, column: 18, scope: !190)
!193 = !DILocation(line: 164, column: 21, scope: !194)
!194 = !DILexicalBlockFile(scope: !23, file: !1, discriminator: 2)
!195 = !DILocation(line: 164, column: 18, scope: !194)
!196 = !DILocation(line: 164, column: 3, scope: !197)
!197 = !DILexicalBlockFile(scope: !183, file: !1, discriminator: 3)
!198 = !DILocation(line: 165, column: 1, scope: !23)
!199 = !DILocalVariable(name: "first", arg: 1, scope: !27, file: !1, line: 169, type: !14)
!200 = !DILocation(line: 169, column: 31, scope: !27)
!201 = !DILocalVariable(name: "second", arg: 2, scope: !27, file: !1, line: 169, type: !14)
!202 = !DILocation(line: 169, column: 50, scope: !27)
!203 = !DILocation(line: 171, column: 30, scope: !27)
!204 = !DILocation(line: 171, column: 37, scope: !27)
!205 = !DILocation(line: 171, column: 10, scope: !27)
!206 = !DILocation(line: 171, column: 3, scope: !27)
!207 = !DILocalVariable(name: "first", arg: 1, scope: !28, file: !1, line: 173, type: !14)
!208 = !DILocation(line: 173, column: 32, scope: !28)
!209 = !DILocalVariable(name: "second", arg: 2, scope: !28, file: !1, line: 173, type: !14)
!210 = !DILocation(line: 173, column: 51, scope: !28)
!211 = !DILocalVariable(name: "max", arg: 3, scope: !28, file: !1, line: 173, type: !20)
!212 = !DILocation(line: 173, column: 66, scope: !28)
!213 = !DILocation(line: 175, column: 31, scope: !28)
!214 = !DILocation(line: 175, column: 38, scope: !28)
!215 = !DILocation(line: 175, column: 46, scope: !28)
!216 = !DILocation(line: 175, column: 10, scope: !28)
!217 = !DILocation(line: 175, column: 3, scope: !28)
