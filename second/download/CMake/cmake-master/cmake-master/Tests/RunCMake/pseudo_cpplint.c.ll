; ModuleID = '/data/download/cmake/cmake-master/Tests/RunCMake/pseudo_cpplint.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }

@.str = private unnamed_addr constant [8 x i8] c"--error\00", align 1
@stderr = external global %struct._IO_FILE*, align 8
@.str.1 = private unnamed_addr constant [41 x i8] c"%s:0:  message  [category/category] [0]\0A\00", align 1
@stdout = external global %struct._IO_FILE*, align 8
@.str.2 = private unnamed_addr constant [43 x i8] c"Done processing %s\0ATotal errors found: %i\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @main(i32 %argc, i8** %argv) #0 !dbg !4 {
entry:
  %retval = alloca i32, align 4
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca i8**, align 8
  %error = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  store i32 %argc, i32* %argc.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %argc.addr, metadata !14, metadata !15), !dbg !16
  store i8** %argv, i8*** %argv.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %argv.addr, metadata !17, metadata !15), !dbg !18
  call void @llvm.dbg.declare(metadata i32* %error, metadata !19, metadata !15), !dbg !20
  store i32 0, i32* %error, align 4, !dbg !20
  call void @llvm.dbg.declare(metadata i32* %i, metadata !21, metadata !15), !dbg !22
  store i32 1, i32* %i, align 4, !dbg !23
  br label %for.cond, !dbg !25

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4, !dbg !26
  %1 = load i32, i32* %argc.addr, align 4, !dbg !29
  %cmp = icmp slt i32 %0, %1, !dbg !30
  br i1 %cmp, label %for.body, label %for.end, !dbg !31

for.body:                                         ; preds = %for.cond
  %2 = load i32, i32* %i, align 4, !dbg !32
  %idxprom = sext i32 %2 to i64, !dbg !35
  %3 = load i8**, i8*** %argv.addr, align 8, !dbg !35
  %arrayidx = getelementptr inbounds i8*, i8** %3, i64 %idxprom, !dbg !35
  %4 = load i8*, i8** %arrayidx, align 8, !dbg !35
  %call = call i32 @strcmp(i8* %4, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0)) #4, !dbg !36
  %cmp1 = icmp eq i32 %call, 0, !dbg !37
  br i1 %cmp1, label %if.then, label %if.end, !dbg !38

if.then:                                          ; preds = %for.body
  store i32 1, i32* %error, align 4, !dbg !39
  br label %if.end, !dbg !41

if.end:                                           ; preds = %if.then, %for.body
  %5 = load i32, i32* %i, align 4, !dbg !42
  %idxprom2 = sext i32 %5 to i64, !dbg !44
  %6 = load i8**, i8*** %argv.addr, align 8, !dbg !44
  %arrayidx3 = getelementptr inbounds i8*, i8** %6, i64 %idxprom2, !dbg !44
  %7 = load i8*, i8** %arrayidx3, align 8, !dbg !44
  %arrayidx4 = getelementptr inbounds i8, i8* %7, i64 0, !dbg !44
  %8 = load i8, i8* %arrayidx4, align 1, !dbg !44
  %conv = sext i8 %8 to i32, !dbg !44
  %cmp5 = icmp ne i32 %conv, 45, !dbg !45
  br i1 %cmp5, label %if.then7, label %if.end16, !dbg !46

if.then7:                                         ; preds = %if.end
  %9 = load i32, i32* %error, align 4, !dbg !47
  %tobool = icmp ne i32 %9, 0, !dbg !47
  br i1 %tobool, label %if.then8, label %if.end12, !dbg !50

if.then8:                                         ; preds = %if.then7
  %10 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !51
  %11 = load i32, i32* %i, align 4, !dbg !53
  %idxprom9 = sext i32 %11 to i64, !dbg !54
  %12 = load i8**, i8*** %argv.addr, align 8, !dbg !54
  %arrayidx10 = getelementptr inbounds i8*, i8** %12, i64 %idxprom9, !dbg !54
  %13 = load i8*, i8** %arrayidx10, align 8, !dbg !54
  %call11 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %10, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.1, i32 0, i32 0), i8* %13), !dbg !55
  br label %if.end12, !dbg !56

if.end12:                                         ; preds = %if.then8, %if.then7
  %14 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !57
  %15 = load i32, i32* %i, align 4, !dbg !58
  %idxprom13 = sext i32 %15 to i64, !dbg !59
  %16 = load i8**, i8*** %argv.addr, align 8, !dbg !59
  %arrayidx14 = getelementptr inbounds i8*, i8** %16, i64 %idxprom13, !dbg !59
  %17 = load i8*, i8** %arrayidx14, align 8, !dbg !59
  %18 = load i32, i32* %error, align 4, !dbg !60
  %call15 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %14, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.2, i32 0, i32 0), i8* %17, i32 %18), !dbg !61
  br label %if.end16, !dbg !62

if.end16:                                         ; preds = %if.end12, %if.end
  br label %for.inc, !dbg !63

for.inc:                                          ; preds = %if.end16
  %19 = load i32, i32* %i, align 4, !dbg !64
  %inc = add nsw i32 %19, 1, !dbg !64
  store i32 %inc, i32* %i, align 4, !dbg !64
  br label %for.cond, !dbg !66

for.end:                                          ; preds = %for.cond
  %20 = load i32, i32* %error, align 4, !dbg !67
  ret i32 %20, !dbg !68
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #2

declare i32 @fprintf(%struct._IO_FILE*, i8*, ...) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!11, !12}
!llvm.ident = !{!13}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Tests/RunCMake/pseudo_cpplint.c", directory: "/data/download/cmake/cmake-master/Tests/RunCMake")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 4, type: !5, isLocal: false, isDefinition: true, scopeLine: 5, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !7, !8}
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!11 = !{i32 2, !"Dwarf Version", i32 4}
!12 = !{i32 2, !"Debug Info Version", i32 3}
!13 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!14 = !DILocalVariable(name: "argc", arg: 1, scope: !4, file: !1, line: 4, type: !7)
!15 = !DIExpression()
!16 = !DILocation(line: 4, column: 14, scope: !4)
!17 = !DILocalVariable(name: "argv", arg: 2, scope: !4, file: !1, line: 4, type: !8)
!18 = !DILocation(line: 4, column: 26, scope: !4)
!19 = !DILocalVariable(name: "error", scope: !4, file: !1, line: 6, type: !7)
!20 = !DILocation(line: 6, column: 7, scope: !4)
!21 = !DILocalVariable(name: "i", scope: !4, file: !1, line: 7, type: !7)
!22 = !DILocation(line: 7, column: 7, scope: !4)
!23 = !DILocation(line: 8, column: 10, scope: !24)
!24 = distinct !DILexicalBlock(scope: !4, file: !1, line: 8, column: 3)
!25 = !DILocation(line: 8, column: 8, scope: !24)
!26 = !DILocation(line: 8, column: 15, scope: !27)
!27 = !DILexicalBlockFile(scope: !28, file: !1, discriminator: 1)
!28 = distinct !DILexicalBlock(scope: !24, file: !1, line: 8, column: 3)
!29 = !DILocation(line: 8, column: 19, scope: !27)
!30 = !DILocation(line: 8, column: 17, scope: !27)
!31 = !DILocation(line: 8, column: 3, scope: !27)
!32 = !DILocation(line: 9, column: 21, scope: !33)
!33 = distinct !DILexicalBlock(scope: !34, file: !1, line: 9, column: 9)
!34 = distinct !DILexicalBlock(scope: !28, file: !1, line: 8, column: 30)
!35 = !DILocation(line: 9, column: 16, scope: !33)
!36 = !DILocation(line: 9, column: 9, scope: !33)
!37 = !DILocation(line: 9, column: 36, scope: !33)
!38 = !DILocation(line: 9, column: 9, scope: !34)
!39 = !DILocation(line: 10, column: 13, scope: !40)
!40 = distinct !DILexicalBlock(scope: !33, file: !1, line: 9, column: 42)
!41 = !DILocation(line: 11, column: 5, scope: !40)
!42 = !DILocation(line: 12, column: 14, scope: !43)
!43 = distinct !DILexicalBlock(scope: !34, file: !1, line: 12, column: 9)
!44 = !DILocation(line: 12, column: 9, scope: !43)
!45 = !DILocation(line: 12, column: 20, scope: !43)
!46 = !DILocation(line: 12, column: 9, scope: !34)
!47 = !DILocation(line: 13, column: 11, scope: !48)
!48 = distinct !DILexicalBlock(scope: !49, file: !1, line: 13, column: 11)
!49 = distinct !DILexicalBlock(scope: !43, file: !1, line: 12, column: 28)
!50 = !DILocation(line: 13, column: 11, scope: !49)
!51 = !DILocation(line: 14, column: 17, scope: !52)
!52 = distinct !DILexicalBlock(scope: !48, file: !1, line: 13, column: 18)
!53 = !DILocation(line: 14, column: 75, scope: !52)
!54 = !DILocation(line: 14, column: 70, scope: !52)
!55 = !DILocation(line: 14, column: 9, scope: !52)
!56 = !DILocation(line: 15, column: 7, scope: !52)
!57 = !DILocation(line: 16, column: 15, scope: !49)
!58 = !DILocation(line: 16, column: 76, scope: !49)
!59 = !DILocation(line: 16, column: 71, scope: !49)
!60 = !DILocation(line: 17, column: 15, scope: !49)
!61 = !DILocation(line: 16, column: 7, scope: !49)
!62 = !DILocation(line: 18, column: 5, scope: !49)
!63 = !DILocation(line: 19, column: 3, scope: !34)
!64 = !DILocation(line: 8, column: 25, scope: !65)
!65 = !DILexicalBlockFile(scope: !28, file: !1, discriminator: 2)
!66 = !DILocation(line: 8, column: 3, scope: !65)
!67 = !DILocation(line: 20, column: 10, scope: !4)
!68 = !DILocation(line: 20, column: 3, scope: !4)
