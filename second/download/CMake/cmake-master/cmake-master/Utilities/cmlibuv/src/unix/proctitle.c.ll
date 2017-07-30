; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/proctitle.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.anon = type { i8*, i64 }

@process_title = internal global %struct.anon zeroinitializer, align 8
@.str = private unnamed_addr constant [30 x i8] c"process_title.len + 1 == size\00", align 1
@.str.1 = private unnamed_addr constant [73 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/proctitle.c\00", align 1
@__PRETTY_FUNCTION__.uv_setup_args = private unnamed_addr constant [35 x i8] c"char **uv_setup_args(int, char **)\00", align 1
@args_mem = internal global i8* null, align 8
@llvm.global_dtors = appending global [1 x { i32, void ()*, i8* }] [{ i32, void ()*, i8* } { i32 65535, void ()* @free_args_mem, i8* null }]

; Function Attrs: nounwind uwtable
define i8** @uv_setup_args(i32 %argc, i8** %argv) #0 !dbg !8 {
entry:
  %retval = alloca i8**, align 8
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca i8**, align 8
  %new_argv = alloca i8**, align 8
  %size = alloca i64, align 8
  %s = alloca i8*, align 8
  %i = alloca i32, align 4
  store i32 %argc, i32* %argc.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %argc.addr, metadata !37, metadata !38), !dbg !39
  store i8** %argv, i8*** %argv.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %argv.addr, metadata !40, metadata !38), !dbg !41
  call void @llvm.dbg.declare(metadata i8*** %new_argv, metadata !42, metadata !38), !dbg !43
  call void @llvm.dbg.declare(metadata i64* %size, metadata !44, metadata !38), !dbg !45
  call void @llvm.dbg.declare(metadata i8** %s, metadata !46, metadata !38), !dbg !47
  call void @llvm.dbg.declare(metadata i32* %i, metadata !48, metadata !38), !dbg !49
  %0 = load i32, i32* %argc.addr, align 4, !dbg !50
  %cmp = icmp sle i32 %0, 0, !dbg !52
  br i1 %cmp, label %if.then, label %if.end, !dbg !53

if.then:                                          ; preds = %entry
  %1 = load i8**, i8*** %argv.addr, align 8, !dbg !54
  store i8** %1, i8*** %retval, align 8, !dbg !55
  br label %return, !dbg !55

if.end:                                           ; preds = %entry
  store i64 0, i64* %size, align 8, !dbg !56
  store i32 0, i32* %i, align 4, !dbg !57
  br label %for.cond, !dbg !59

for.cond:                                         ; preds = %for.inc, %if.end
  %2 = load i32, i32* %i, align 4, !dbg !60
  %3 = load i32, i32* %argc.addr, align 4, !dbg !63
  %cmp1 = icmp slt i32 %2, %3, !dbg !64
  br i1 %cmp1, label %for.body, label %for.end, !dbg !65

for.body:                                         ; preds = %for.cond
  %4 = load i32, i32* %i, align 4, !dbg !66
  %idxprom = sext i32 %4 to i64, !dbg !67
  %5 = load i8**, i8*** %argv.addr, align 8, !dbg !67
  %arrayidx = getelementptr inbounds i8*, i8** %5, i64 %idxprom, !dbg !67
  %6 = load i8*, i8** %arrayidx, align 8, !dbg !67
  %call = call i64 @strlen(i8* %6) #7, !dbg !68
  %add = add i64 %call, 1, !dbg !69
  %7 = load i64, i64* %size, align 8, !dbg !70
  %add2 = add i64 %7, %add, !dbg !70
  store i64 %add2, i64* %size, align 8, !dbg !70
  br label %for.inc, !dbg !71

for.inc:                                          ; preds = %for.body
  %8 = load i32, i32* %i, align 4, !dbg !72
  %inc = add nsw i32 %8, 1, !dbg !72
  store i32 %inc, i32* %i, align 4, !dbg !72
  br label %for.cond, !dbg !74

for.end:                                          ; preds = %for.cond
  %9 = load i8**, i8*** %argv.addr, align 8, !dbg !75
  %arrayidx3 = getelementptr inbounds i8*, i8** %9, i64 0, !dbg !75
  %10 = load i8*, i8** %arrayidx3, align 8, !dbg !75
  store i8* %10, i8** getelementptr inbounds (%struct.anon, %struct.anon* @process_title, i32 0, i32 0), align 8, !dbg !76
  %11 = load i32, i32* %argc.addr, align 4, !dbg !77
  %sub = sub nsw i32 %11, 1, !dbg !78
  %idxprom4 = sext i32 %sub to i64, !dbg !79
  %12 = load i8**, i8*** %argv.addr, align 8, !dbg !79
  %arrayidx5 = getelementptr inbounds i8*, i8** %12, i64 %idxprom4, !dbg !79
  %13 = load i8*, i8** %arrayidx5, align 8, !dbg !79
  %14 = load i32, i32* %argc.addr, align 4, !dbg !80
  %sub6 = sub nsw i32 %14, 1, !dbg !81
  %idxprom7 = sext i32 %sub6 to i64, !dbg !82
  %15 = load i8**, i8*** %argv.addr, align 8, !dbg !82
  %arrayidx8 = getelementptr inbounds i8*, i8** %15, i64 %idxprom7, !dbg !82
  %16 = load i8*, i8** %arrayidx8, align 8, !dbg !82
  %call9 = call i64 @strlen(i8* %16) #7, !dbg !83
  %add.ptr = getelementptr inbounds i8, i8* %13, i64 %call9, !dbg !84
  %17 = load i8**, i8*** %argv.addr, align 8, !dbg !85
  %arrayidx10 = getelementptr inbounds i8*, i8** %17, i64 0, !dbg !85
  %18 = load i8*, i8** %arrayidx10, align 8, !dbg !85
  %sub.ptr.lhs.cast = ptrtoint i8* %add.ptr to i64, !dbg !86
  %sub.ptr.rhs.cast = ptrtoint i8* %18 to i64, !dbg !86
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !86
  store i64 %sub.ptr.sub, i64* getelementptr inbounds (%struct.anon, %struct.anon* @process_title, i32 0, i32 1), align 8, !dbg !87
  %19 = load i64, i64* getelementptr inbounds (%struct.anon, %struct.anon* @process_title, i32 0, i32 1), align 8, !dbg !88
  %add11 = add i64 %19, 1, !dbg !88
  %20 = load i64, i64* %size, align 8, !dbg !88
  %cmp12 = icmp eq i64 %add11, %20, !dbg !88
  br i1 %cmp12, label %cond.true, label %cond.false, !dbg !88

cond.true:                                        ; preds = %for.end
  br label %cond.end, !dbg !89

cond.false:                                       ; preds = %for.end
  call void @__assert_fail(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([73 x i8], [73 x i8]* @.str.1, i32 0, i32 0), i32 58, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @__PRETTY_FUNCTION__.uv_setup_args, i32 0, i32 0)) #8, !dbg !91
  unreachable, !dbg !91
                                                  ; No predecessors!
  br label %cond.end, !dbg !93

cond.end:                                         ; preds = %21, %cond.true
  %22 = load i32, i32* %argc.addr, align 4, !dbg !95
  %add13 = add nsw i32 %22, 1, !dbg !96
  %conv = sext i32 %add13 to i64, !dbg !97
  %mul = mul i64 %conv, 8, !dbg !98
  %23 = load i64, i64* %size, align 8, !dbg !99
  %add14 = add i64 %23, %mul, !dbg !99
  store i64 %add14, i64* %size, align 8, !dbg !99
  %24 = load i64, i64* %size, align 8, !dbg !100
  %call15 = call i8* @uv__malloc(i64 %24), !dbg !101
  %25 = bitcast i8* %call15 to i8**, !dbg !101
  store i8** %25, i8*** %new_argv, align 8, !dbg !102
  %26 = load i8**, i8*** %new_argv, align 8, !dbg !103
  %cmp16 = icmp eq i8** %26, null, !dbg !105
  br i1 %cmp16, label %if.then18, label %if.end19, !dbg !106

if.then18:                                        ; preds = %cond.end
  %27 = load i8**, i8*** %argv.addr, align 8, !dbg !107
  store i8** %27, i8*** %retval, align 8, !dbg !108
  br label %return, !dbg !108

if.end19:                                         ; preds = %cond.end
  %28 = load i8**, i8*** %new_argv, align 8, !dbg !109
  %29 = bitcast i8** %28 to i8*, !dbg !109
  store i8* %29, i8** @args_mem, align 8, !dbg !110
  %30 = load i32, i32* %argc.addr, align 4, !dbg !111
  %add20 = add nsw i32 %30, 1, !dbg !112
  %idxprom21 = sext i32 %add20 to i64, !dbg !113
  %31 = load i8**, i8*** %new_argv, align 8, !dbg !113
  %arrayidx22 = getelementptr inbounds i8*, i8** %31, i64 %idxprom21, !dbg !113
  %32 = bitcast i8** %arrayidx22 to i8*, !dbg !114
  store i8* %32, i8** %s, align 8, !dbg !115
  store i32 0, i32* %i, align 4, !dbg !116
  br label %for.cond23, !dbg !118

for.cond23:                                       ; preds = %for.inc36, %if.end19
  %33 = load i32, i32* %i, align 4, !dbg !119
  %34 = load i32, i32* %argc.addr, align 4, !dbg !122
  %cmp24 = icmp slt i32 %33, %34, !dbg !123
  br i1 %cmp24, label %for.body26, label %for.end38, !dbg !124

for.body26:                                       ; preds = %for.cond23
  %35 = load i32, i32* %i, align 4, !dbg !125
  %idxprom27 = sext i32 %35 to i64, !dbg !127
  %36 = load i8**, i8*** %argv.addr, align 8, !dbg !127
  %arrayidx28 = getelementptr inbounds i8*, i8** %36, i64 %idxprom27, !dbg !127
  %37 = load i8*, i8** %arrayidx28, align 8, !dbg !127
  %call29 = call i64 @strlen(i8* %37) #7, !dbg !128
  %add30 = add i64 %call29, 1, !dbg !129
  store i64 %add30, i64* %size, align 8, !dbg !130
  %38 = load i8*, i8** %s, align 8, !dbg !131
  %39 = load i32, i32* %i, align 4, !dbg !132
  %idxprom31 = sext i32 %39 to i64, !dbg !133
  %40 = load i8**, i8*** %argv.addr, align 8, !dbg !133
  %arrayidx32 = getelementptr inbounds i8*, i8** %40, i64 %idxprom31, !dbg !133
  %41 = load i8*, i8** %arrayidx32, align 8, !dbg !133
  %42 = load i64, i64* %size, align 8, !dbg !134
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %38, i8* %41, i64 %42, i32 1, i1 false), !dbg !135
  %43 = load i8*, i8** %s, align 8, !dbg !136
  %44 = load i32, i32* %i, align 4, !dbg !137
  %idxprom33 = sext i32 %44 to i64, !dbg !138
  %45 = load i8**, i8*** %new_argv, align 8, !dbg !138
  %arrayidx34 = getelementptr inbounds i8*, i8** %45, i64 %idxprom33, !dbg !138
  store i8* %43, i8** %arrayidx34, align 8, !dbg !139
  %46 = load i64, i64* %size, align 8, !dbg !140
  %47 = load i8*, i8** %s, align 8, !dbg !141
  %add.ptr35 = getelementptr inbounds i8, i8* %47, i64 %46, !dbg !141
  store i8* %add.ptr35, i8** %s, align 8, !dbg !141
  br label %for.inc36, !dbg !142

for.inc36:                                        ; preds = %for.body26
  %48 = load i32, i32* %i, align 4, !dbg !143
  %inc37 = add nsw i32 %48, 1, !dbg !143
  store i32 %inc37, i32* %i, align 4, !dbg !143
  br label %for.cond23, !dbg !145

for.end38:                                        ; preds = %for.cond23
  %49 = load i32, i32* %i, align 4, !dbg !146
  %idxprom39 = sext i32 %49 to i64, !dbg !147
  %50 = load i8**, i8*** %new_argv, align 8, !dbg !147
  %arrayidx40 = getelementptr inbounds i8*, i8** %50, i64 %idxprom39, !dbg !147
  store i8* null, i8** %arrayidx40, align 8, !dbg !148
  %51 = load i8**, i8*** %new_argv, align 8, !dbg !149
  store i8** %51, i8*** %retval, align 8, !dbg !150
  br label %return, !dbg !150

return:                                           ; preds = %for.end38, %if.then18, %if.then
  %52 = load i8**, i8*** %retval, align 8, !dbg !151
  ret i8** %52, !dbg !151
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #2

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #3

declare i8* @uv__malloc(i64) #4

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

; Function Attrs: nounwind uwtable
define i32 @uv_set_process_title(i8* %title) #0 !dbg !13 {
entry:
  %retval = alloca i32, align 4
  %title.addr = alloca i8*, align 8
  store i8* %title, i8** %title.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %title.addr, metadata !152, metadata !38), !dbg !153
  %0 = load i64, i64* getelementptr inbounds (%struct.anon, %struct.anon* @process_title, i32 0, i32 1), align 8, !dbg !154
  %cmp = icmp eq i64 %0, 0, !dbg !156
  br i1 %cmp, label %if.then, label %if.end, !dbg !157

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !158
  br label %return, !dbg !158

if.end:                                           ; preds = %entry
  %1 = load i8*, i8** getelementptr inbounds (%struct.anon, %struct.anon* @process_title, i32 0, i32 0), align 8, !dbg !159
  %2 = load i8*, i8** %title.addr, align 8, !dbg !160
  %3 = load i64, i64* getelementptr inbounds (%struct.anon, %struct.anon* @process_title, i32 0, i32 1), align 8, !dbg !161
  %call = call i8* @strncpy(i8* %1, i8* %2, i64 %3) #9, !dbg !162
  %4 = load i8*, i8** %title.addr, align 8, !dbg !163
  call void @uv__set_process_title(i8* %4), !dbg !164
  store i32 0, i32* %retval, align 4, !dbg !165
  br label %return, !dbg !165

return:                                           ; preds = %if.end, %if.then
  %5 = load i32, i32* %retval, align 4, !dbg !166
  ret i32 %5, !dbg !166
}

; Function Attrs: nounwind
declare i8* @strncpy(i8*, i8*, i64) #6

declare void @uv__set_process_title(i8*) #4

; Function Attrs: nounwind uwtable
define i32 @uv_get_process_title(i8* %buffer, i64 %size) #0 !dbg !18 {
entry:
  %retval = alloca i32, align 4
  %buffer.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !167, metadata !38), !dbg !168
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !169, metadata !38), !dbg !170
  %0 = load i8*, i8** %buffer.addr, align 8, !dbg !171
  %cmp = icmp eq i8* %0, null, !dbg !173
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !174

lor.lhs.false:                                    ; preds = %entry
  %1 = load i64, i64* %size.addr, align 8, !dbg !175
  %cmp1 = icmp eq i64 %1, 0, !dbg !177
  br i1 %cmp1, label %if.then, label %if.else, !dbg !178

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -22, i32* %retval, align 4, !dbg !179
  br label %return, !dbg !179

if.else:                                          ; preds = %lor.lhs.false
  %2 = load i64, i64* %size.addr, align 8, !dbg !180
  %3 = load i64, i64* getelementptr inbounds (%struct.anon, %struct.anon* @process_title, i32 0, i32 1), align 8, !dbg !182
  %cmp2 = icmp ule i64 %2, %3, !dbg !183
  br i1 %cmp2, label %if.then3, label %if.end, !dbg !184

if.then3:                                         ; preds = %if.else
  store i32 -105, i32* %retval, align 4, !dbg !185
  br label %return, !dbg !185

if.end:                                           ; preds = %if.else
  br label %if.end4

if.end4:                                          ; preds = %if.end
  %4 = load i8*, i8** %buffer.addr, align 8, !dbg !186
  %5 = load i8*, i8** getelementptr inbounds (%struct.anon, %struct.anon* @process_title, i32 0, i32 0), align 8, !dbg !187
  %6 = load i64, i64* getelementptr inbounds (%struct.anon, %struct.anon* @process_title, i32 0, i32 1), align 8, !dbg !188
  %add = add i64 %6, 1, !dbg !189
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %4, i8* %5, i64 %add, i32 1, i1 false), !dbg !190
  %7 = load i64, i64* getelementptr inbounds (%struct.anon, %struct.anon* @process_title, i32 0, i32 1), align 8, !dbg !191
  %8 = load i8*, i8** %buffer.addr, align 8, !dbg !192
  %arrayidx = getelementptr inbounds i8, i8* %8, i64 %7, !dbg !192
  store i8 0, i8* %arrayidx, align 1, !dbg !193
  store i32 0, i32* %retval, align 4, !dbg !194
  br label %return, !dbg !194

return:                                           ; preds = %if.end4, %if.then3, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !195
  ret i32 %9, !dbg !195
}

; Function Attrs: nounwind uwtable
define internal void @free_args_mem() #0 !dbg !24 {
entry:
  %0 = load i8*, i8** @args_mem, align 8, !dbg !196
  call void @uv__free(i8* %0), !dbg !197
  store i8* null, i8** @args_mem, align 8, !dbg !198
  ret void, !dbg !199
}

declare void @uv__free(i8*) #4

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind readonly }
attributes #8 = { noreturn nounwind }
attributes #9 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!34, !35}
!llvm.ident = !{!36}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !7, globals: !27)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/proctitle.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{}
!3 = !{!4, !5}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64, align: 64)
!6 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!7 = !{!8, !13, !18, !24}
!8 = distinct !DISubprogram(name: "uv_setup_args", scope: !1, file: !1, line: 37, type: !9, isLocal: false, isDefinition: true, scopeLine: 37, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!9 = !DISubroutineType(types: !10)
!10 = !{!11, !12, !11}
!11 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!12 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!13 = distinct !DISubprogram(name: "uv_set_process_title", scope: !1, file: !1, line: 83, type: !14, isLocal: false, isDefinition: true, scopeLine: 83, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!14 = !DISubroutineType(types: !15)
!15 = !{!12, !16}
!16 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !17, size: 64, align: 64)
!17 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !6)
!18 = distinct !DISubprogram(name: "uv_get_process_title", scope: !1, file: !1, line: 95, type: !19, isLocal: false, isDefinition: true, scopeLine: 95, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!19 = !DISubroutineType(types: !20)
!20 = !{!12, !5, !21}
!21 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !22, line: 62, baseType: !23)
!22 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!23 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!24 = distinct !DISubprogram(name: "free_args_mem", scope: !1, file: !1, line: 108, type: !25, isLocal: true, isDefinition: true, scopeLine: 108, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!25 = !DISubroutineType(types: !26)
!26 = !{null}
!27 = !{!28, !29}
!28 = !DIGlobalVariable(name: "args_mem", scope: !0, file: !1, line: 29, type: !4, isLocal: true, isDefinition: true, variable: i8** @args_mem)
!29 = !DIGlobalVariable(name: "process_title", scope: !0, file: !1, line: 34, type: !30, isLocal: true, isDefinition: true, variable: %struct.anon* @process_title)
!30 = !DICompositeType(tag: DW_TAG_structure_type, file: !1, line: 31, size: 128, align: 64, elements: !31)
!31 = !{!32, !33}
!32 = !DIDerivedType(tag: DW_TAG_member, name: "str", scope: !30, file: !1, line: 32, baseType: !5, size: 64, align: 64)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !30, file: !1, line: 33, baseType: !21, size: 64, align: 64, offset: 64)
!34 = !{i32 2, !"Dwarf Version", i32 4}
!35 = !{i32 2, !"Debug Info Version", i32 3}
!36 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!37 = !DILocalVariable(name: "argc", arg: 1, scope: !8, file: !1, line: 37, type: !12)
!38 = !DIExpression()
!39 = !DILocation(line: 37, column: 26, scope: !8)
!40 = !DILocalVariable(name: "argv", arg: 2, scope: !8, file: !1, line: 37, type: !11)
!41 = !DILocation(line: 37, column: 39, scope: !8)
!42 = !DILocalVariable(name: "new_argv", scope: !8, file: !1, line: 38, type: !11)
!43 = !DILocation(line: 38, column: 10, scope: !8)
!44 = !DILocalVariable(name: "size", scope: !8, file: !1, line: 39, type: !21)
!45 = !DILocation(line: 39, column: 10, scope: !8)
!46 = !DILocalVariable(name: "s", scope: !8, file: !1, line: 40, type: !5)
!47 = !DILocation(line: 40, column: 9, scope: !8)
!48 = !DILocalVariable(name: "i", scope: !8, file: !1, line: 41, type: !12)
!49 = !DILocation(line: 41, column: 7, scope: !8)
!50 = !DILocation(line: 43, column: 7, scope: !51)
!51 = distinct !DILexicalBlock(scope: !8, file: !1, line: 43, column: 7)
!52 = !DILocation(line: 43, column: 12, scope: !51)
!53 = !DILocation(line: 43, column: 7, scope: !8)
!54 = !DILocation(line: 44, column: 12, scope: !51)
!55 = !DILocation(line: 44, column: 5, scope: !51)
!56 = !DILocation(line: 47, column: 8, scope: !8)
!57 = !DILocation(line: 48, column: 10, scope: !58)
!58 = distinct !DILexicalBlock(scope: !8, file: !1, line: 48, column: 3)
!59 = !DILocation(line: 48, column: 8, scope: !58)
!60 = !DILocation(line: 48, column: 15, scope: !61)
!61 = !DILexicalBlockFile(scope: !62, file: !1, discriminator: 1)
!62 = distinct !DILexicalBlock(scope: !58, file: !1, line: 48, column: 3)
!63 = !DILocation(line: 48, column: 19, scope: !61)
!64 = !DILocation(line: 48, column: 17, scope: !61)
!65 = !DILocation(line: 48, column: 3, scope: !61)
!66 = !DILocation(line: 49, column: 25, scope: !62)
!67 = !DILocation(line: 49, column: 20, scope: !62)
!68 = !DILocation(line: 49, column: 13, scope: !62)
!69 = !DILocation(line: 49, column: 29, scope: !62)
!70 = !DILocation(line: 49, column: 10, scope: !62)
!71 = !DILocation(line: 49, column: 5, scope: !62)
!72 = !DILocation(line: 48, column: 26, scope: !73)
!73 = !DILexicalBlockFile(scope: !62, file: !1, discriminator: 2)
!74 = !DILocation(line: 48, column: 3, scope: !73)
!75 = !DILocation(line: 56, column: 23, scope: !8)
!76 = !DILocation(line: 56, column: 21, scope: !8)
!77 = !DILocation(line: 57, column: 28, scope: !8)
!78 = !DILocation(line: 57, column: 33, scope: !8)
!79 = !DILocation(line: 57, column: 23, scope: !8)
!80 = !DILocation(line: 57, column: 52, scope: !8)
!81 = !DILocation(line: 57, column: 57, scope: !8)
!82 = !DILocation(line: 57, column: 47, scope: !8)
!83 = !DILocation(line: 57, column: 40, scope: !8)
!84 = !DILocation(line: 57, column: 38, scope: !8)
!85 = !DILocation(line: 57, column: 65, scope: !8)
!86 = !DILocation(line: 57, column: 63, scope: !8)
!87 = !DILocation(line: 57, column: 21, scope: !8)
!88 = !DILocation(line: 58, column: 3, scope: !8)
!89 = !DILocation(line: 58, column: 3, scope: !90)
!90 = !DILexicalBlockFile(scope: !8, file: !1, discriminator: 1)
!91 = !DILocation(line: 58, column: 3, scope: !92)
!92 = !DILexicalBlockFile(scope: !8, file: !1, discriminator: 2)
!93 = !DILocation(line: 58, column: 3, scope: !94)
!94 = !DILexicalBlockFile(scope: !8, file: !1, discriminator: 3)
!95 = !DILocation(line: 62, column: 12, scope: !8)
!96 = !DILocation(line: 62, column: 17, scope: !8)
!97 = !DILocation(line: 62, column: 11, scope: !8)
!98 = !DILocation(line: 62, column: 22, scope: !8)
!99 = !DILocation(line: 62, column: 8, scope: !8)
!100 = !DILocation(line: 64, column: 25, scope: !8)
!101 = !DILocation(line: 64, column: 14, scope: !8)
!102 = !DILocation(line: 64, column: 12, scope: !8)
!103 = !DILocation(line: 65, column: 7, scope: !104)
!104 = distinct !DILexicalBlock(scope: !8, file: !1, line: 65, column: 7)
!105 = !DILocation(line: 65, column: 16, scope: !104)
!106 = !DILocation(line: 65, column: 7, scope: !8)
!107 = !DILocation(line: 66, column: 12, scope: !104)
!108 = !DILocation(line: 66, column: 5, scope: !104)
!109 = !DILocation(line: 67, column: 14, scope: !8)
!110 = !DILocation(line: 67, column: 12, scope: !8)
!111 = !DILocation(line: 70, column: 25, scope: !8)
!112 = !DILocation(line: 70, column: 30, scope: !8)
!113 = !DILocation(line: 70, column: 16, scope: !8)
!114 = !DILocation(line: 70, column: 7, scope: !8)
!115 = !DILocation(line: 70, column: 5, scope: !8)
!116 = !DILocation(line: 71, column: 10, scope: !117)
!117 = distinct !DILexicalBlock(scope: !8, file: !1, line: 71, column: 3)
!118 = !DILocation(line: 71, column: 8, scope: !117)
!119 = !DILocation(line: 71, column: 15, scope: !120)
!120 = !DILexicalBlockFile(scope: !121, file: !1, discriminator: 1)
!121 = distinct !DILexicalBlock(scope: !117, file: !1, line: 71, column: 3)
!122 = !DILocation(line: 71, column: 19, scope: !120)
!123 = !DILocation(line: 71, column: 17, scope: !120)
!124 = !DILocation(line: 71, column: 3, scope: !120)
!125 = !DILocation(line: 72, column: 24, scope: !126)
!126 = distinct !DILexicalBlock(scope: !121, file: !1, line: 71, column: 30)
!127 = !DILocation(line: 72, column: 19, scope: !126)
!128 = !DILocation(line: 72, column: 12, scope: !126)
!129 = !DILocation(line: 72, column: 28, scope: !126)
!130 = !DILocation(line: 72, column: 10, scope: !126)
!131 = !DILocation(line: 73, column: 12, scope: !126)
!132 = !DILocation(line: 73, column: 20, scope: !126)
!133 = !DILocation(line: 73, column: 15, scope: !126)
!134 = !DILocation(line: 73, column: 24, scope: !126)
!135 = !DILocation(line: 73, column: 5, scope: !126)
!136 = !DILocation(line: 74, column: 19, scope: !126)
!137 = !DILocation(line: 74, column: 14, scope: !126)
!138 = !DILocation(line: 74, column: 5, scope: !126)
!139 = !DILocation(line: 74, column: 17, scope: !126)
!140 = !DILocation(line: 75, column: 10, scope: !126)
!141 = !DILocation(line: 75, column: 7, scope: !126)
!142 = !DILocation(line: 76, column: 3, scope: !126)
!143 = !DILocation(line: 71, column: 26, scope: !144)
!144 = !DILexicalBlockFile(scope: !121, file: !1, discriminator: 2)
!145 = !DILocation(line: 71, column: 3, scope: !144)
!146 = !DILocation(line: 77, column: 12, scope: !8)
!147 = !DILocation(line: 77, column: 3, scope: !8)
!148 = !DILocation(line: 77, column: 15, scope: !8)
!149 = !DILocation(line: 79, column: 10, scope: !8)
!150 = !DILocation(line: 79, column: 3, scope: !8)
!151 = !DILocation(line: 80, column: 1, scope: !8)
!152 = !DILocalVariable(name: "title", arg: 1, scope: !13, file: !1, line: 83, type: !16)
!153 = !DILocation(line: 83, column: 38, scope: !13)
!154 = !DILocation(line: 84, column: 21, scope: !155)
!155 = distinct !DILexicalBlock(scope: !13, file: !1, line: 84, column: 7)
!156 = !DILocation(line: 84, column: 25, scope: !155)
!157 = !DILocation(line: 84, column: 7, scope: !13)
!158 = !DILocation(line: 85, column: 5, scope: !155)
!159 = !DILocation(line: 88, column: 25, scope: !13)
!160 = !DILocation(line: 88, column: 30, scope: !13)
!161 = !DILocation(line: 88, column: 51, scope: !13)
!162 = !DILocation(line: 88, column: 3, scope: !13)
!163 = !DILocation(line: 89, column: 25, scope: !13)
!164 = !DILocation(line: 89, column: 3, scope: !13)
!165 = !DILocation(line: 91, column: 3, scope: !13)
!166 = !DILocation(line: 92, column: 1, scope: !13)
!167 = !DILocalVariable(name: "buffer", arg: 1, scope: !18, file: !1, line: 95, type: !5)
!168 = !DILocation(line: 95, column: 32, scope: !18)
!169 = !DILocalVariable(name: "size", arg: 2, scope: !18, file: !1, line: 95, type: !21)
!170 = !DILocation(line: 95, column: 47, scope: !18)
!171 = !DILocation(line: 96, column: 7, scope: !172)
!172 = distinct !DILexicalBlock(scope: !18, file: !1, line: 96, column: 7)
!173 = !DILocation(line: 96, column: 14, scope: !172)
!174 = !DILocation(line: 96, column: 22, scope: !172)
!175 = !DILocation(line: 96, column: 25, scope: !176)
!176 = !DILexicalBlockFile(scope: !172, file: !1, discriminator: 1)
!177 = !DILocation(line: 96, column: 30, scope: !176)
!178 = !DILocation(line: 96, column: 7, scope: !176)
!179 = !DILocation(line: 97, column: 5, scope: !172)
!180 = !DILocation(line: 98, column: 12, scope: !181)
!181 = distinct !DILexicalBlock(scope: !172, file: !1, line: 98, column: 12)
!182 = !DILocation(line: 98, column: 34, scope: !181)
!183 = !DILocation(line: 98, column: 17, scope: !181)
!184 = !DILocation(line: 98, column: 12, scope: !172)
!185 = !DILocation(line: 99, column: 5, scope: !181)
!186 = !DILocation(line: 101, column: 10, scope: !18)
!187 = !DILocation(line: 101, column: 32, scope: !18)
!188 = !DILocation(line: 101, column: 51, scope: !18)
!189 = !DILocation(line: 101, column: 55, scope: !18)
!190 = !DILocation(line: 101, column: 3, scope: !18)
!191 = !DILocation(line: 102, column: 24, scope: !18)
!192 = !DILocation(line: 102, column: 3, scope: !18)
!193 = !DILocation(line: 102, column: 29, scope: !18)
!194 = !DILocation(line: 104, column: 3, scope: !18)
!195 = !DILocation(line: 105, column: 1, scope: !18)
!196 = !DILocation(line: 109, column: 12, scope: !24)
!197 = !DILocation(line: 109, column: 3, scope: !24)
!198 = !DILocation(line: 110, column: 12, scope: !24)
!199 = !DILocation(line: 111, column: 1, scope: !24)
